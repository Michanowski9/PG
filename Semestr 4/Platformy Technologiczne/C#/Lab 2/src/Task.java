public class Task {
    private final int jobId;
    private final int precision;

    private static int lastJobId = 0;

    public Task(int precision) {
        Task.lastJobId++;
        this.jobId = lastJobId;
        this.precision = precision;
    }

    public int getJobId() {
        return jobId;
    }

    public int getPrecision() {
        return precision;
    }
}
